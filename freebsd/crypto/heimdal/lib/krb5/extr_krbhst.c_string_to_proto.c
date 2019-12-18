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

/* Variables and functions */
 int KRB5_KRBHST_HTTP ; 
 int KRB5_KRBHST_TCP ; 
 int KRB5_KRBHST_UDP ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
string_to_proto(const char *string)
{
    if(strcasecmp(string, "udp") == 0)
	return KRB5_KRBHST_UDP;
    else if(strcasecmp(string, "tcp") == 0)
	return KRB5_KRBHST_TCP;
    else if(strcasecmp(string, "http") == 0)
	return KRB5_KRBHST_HTTP;
    return -1;
}