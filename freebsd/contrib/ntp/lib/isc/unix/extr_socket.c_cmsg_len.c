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
struct cmsghdr {int dummy; } ;
typedef  scalar_t__ ISC_SOCKADDR_LEN_T ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 scalar_t__ CMSG_LEN (scalar_t__) ; 

__attribute__((used)) static inline ISC_SOCKADDR_LEN_T
cmsg_len(ISC_SOCKADDR_LEN_T len) {
#ifdef CMSG_LEN
	return (CMSG_LEN(len));
#else
	ISC_SOCKADDR_LEN_T hdrlen;

	/*
	 * Cast NULL so that any pointer arithmetic performed by CMSG_DATA
	 * is correct.
	 */
	hdrlen = (ISC_SOCKADDR_LEN_T)CMSG_DATA(((struct cmsghdr *)NULL));
	return (hdrlen + len);
#endif
}