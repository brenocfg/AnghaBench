#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct sockaddr_storage {int dummy; } ;
struct sldns_buffer {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  data; } ;
struct infra_cache {int dummy; } ;
struct comm_reply {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  qnm ;
typedef  int /*<<< orphan*/  client_ip ;

/* Variables and functions */
 scalar_t__ LDNS_HEADER_SIZE ; 
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 scalar_t__ LDNS_QDCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERB_OPS ; 
 int /*<<< orphan*/  addr_to_str (struct sockaddr_storage*,int /*<<< orphan*/ ,char*,int) ; 
 struct lruhash_entry* infra_find_ip_ratedata (struct infra_cache*,struct comm_reply*,int) ; 
 int /*<<< orphan*/  infra_ip_create_ratedata (struct infra_cache*,struct comm_reply*,int /*<<< orphan*/ ) ; 
 int infra_ip_ratelimit ; 
 int* infra_rate_find_second (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int infra_rate_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_at (struct sldns_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_begin (struct sldns_buffer*) ; 
 scalar_t__ sldns_buffer_limit (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_wire2str_rrquestion_buf (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*,int,...) ; 

int infra_ip_ratelimit_inc(struct infra_cache* infra,
  struct comm_reply* repinfo, time_t timenow, struct sldns_buffer* buffer)
{
	int max;
	struct lruhash_entry* entry;

	/* not enabled */
	if(!infra_ip_ratelimit) {
		return 1;
	}
	/* find or insert ratedata */
	entry = infra_find_ip_ratedata(infra, repinfo, 1);
	if(entry) {
		int premax = infra_rate_max(entry->data, timenow);
		int* cur = infra_rate_find_second(entry->data, timenow);
		(*cur)++;
		max = infra_rate_max(entry->data, timenow);
		lock_rw_unlock(&entry->lock);

		if(premax < infra_ip_ratelimit && max >= infra_ip_ratelimit) {
			char client_ip[128], qnm[LDNS_MAX_DOMAINLEN+1+12+12];
			addr_to_str((struct sockaddr_storage *)&repinfo->addr,
				repinfo->addrlen, client_ip, sizeof(client_ip));
			qnm[0]=0;
			if(sldns_buffer_limit(buffer)>LDNS_HEADER_SIZE &&
				LDNS_QDCOUNT(sldns_buffer_begin(buffer))!=0) {
				(void)sldns_wire2str_rrquestion_buf(
					sldns_buffer_at(buffer, LDNS_HEADER_SIZE),
					sldns_buffer_limit(buffer)-LDNS_HEADER_SIZE,
					qnm, sizeof(qnm));
				if(strlen(qnm)>0 && qnm[strlen(qnm)-1]=='\n')
					qnm[strlen(qnm)-1] = 0; /*remove newline*/
				if(strchr(qnm, '\t'))
					*strchr(qnm, '\t') = ' ';
				if(strchr(qnm, '\t'))
					*strchr(qnm, '\t') = ' ';
				verbose(VERB_OPS, "ip_ratelimit exceeded %s %d %s",
					client_ip, infra_ip_ratelimit, qnm);
			} else {
				verbose(VERB_OPS, "ip_ratelimit exceeded %s %d (no query name)",
					client_ip, infra_ip_ratelimit);
			}
		}
		return (max <= infra_ip_ratelimit);
	}

	/* create */
	infra_ip_create_ratedata(infra, repinfo, timenow);
	return 1;
}