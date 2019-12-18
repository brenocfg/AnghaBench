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
typedef  int /*<<< orphan*/  uint8_t ;
struct sockaddr_storage {int dummy; } ;
struct delegpt {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  delegpt_add_ns_mlc (struct delegpt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delegpt_add_target_mlc (struct delegpt*,int /*<<< orphan*/ *,size_t,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extstrtoaddr (char const*,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/ * sldns_str2wire_dname (char const*,size_t*) ; 

__attribute__((used)) static int
ah(struct delegpt* dp, const char* sv, const char* ip)
{
	struct sockaddr_storage addr;
	socklen_t addrlen;
	size_t dname_len;
	uint8_t* dname = sldns_str2wire_dname(sv, &dname_len);
	if(!dname) {
		log_err("could not parse %s", sv);
		return 0;
	}
	if(!delegpt_add_ns_mlc(dp, dname, 0) ||
	   !extstrtoaddr(ip, &addr, &addrlen) ||
	   !delegpt_add_target_mlc(dp, dname, dname_len,
		&addr, addrlen, 0, 0)) {
		free(dname);
		return 0;
	}
	free(dname);
	return 1;
}