#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  token_t ;
struct TYPE_3__ {scalar_t__ at_type; int /*<<< orphan*/ * at_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AUE_NULL ; 
 scalar_t__ AU_IPv4 ; 
 scalar_t__ AU_IPv6 ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/ * au_to_subject32_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  inet_pton (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  subject32_auid ; 
 int /*<<< orphan*/  subject32_egid ; 
 int /*<<< orphan*/  subject32_euid ; 
 int /*<<< orphan*/  subject32_pid ; 
 int /*<<< orphan*/  subject32_rgid ; 
 int /*<<< orphan*/  subject32_ruid ; 
 int /*<<< orphan*/  subject32_sid ; 
 TYPE_1__ subject32_tid_addr ; 
 int /*<<< orphan*/  write_record (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
generate_subject32ex_record(const char *directory, const char *record_filename,
    u_int32_t type)
{
	token_t *subject32ex_token;
	char *buf;

	buf = (char *)malloc(strlen(record_filename) + 6);
	if (type == AU_IPv6) {
		inet_pton(AF_INET6, "fe80::1", subject32_tid_addr.at_addr);
		subject32_tid_addr.at_type = AU_IPv6;
		sprintf(buf, "%s%s", record_filename, "-IPv6");
	} else {
		subject32_tid_addr.at_addr[0] = inet_addr("127.0.0.1");
		subject32_tid_addr.at_type = AU_IPv4;
		sprintf(buf, "%s%s", record_filename, "-IPv4");
	}

	subject32ex_token = au_to_subject32_ex(subject32_auid, subject32_euid,
	    subject32_egid, subject32_ruid, subject32_rgid, subject32_pid,
	    subject32_sid, &subject32_tid_addr);
	if (subject32ex_token == NULL)
		err(EX_UNAVAILABLE, "au_to_subject32_ex");
	write_record(directory, record_filename, subject32ex_token, AUE_NULL);
	free(buf);
}