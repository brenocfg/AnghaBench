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
struct sockaddr_storage {int ss_len; int ss_family; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 

__attribute__((used)) static socklen_t
sockaddr_len(const struct sockaddr_storage *ss)
{

#ifdef HAVE_SOCKADDR_STORAGE_SS_LEN
	return (ss->ss_len);
#else
	switch (ss->ss_family) {
	case AF_INET:
		return (sizeof(struct sockaddr_in));
	case AF_INET6:
		return (sizeof(struct sockaddr_in6));
	default:
		PJDLOG_ABORT("Unexpected family %hhu.", ss->ss_family);
	}
#endif
}