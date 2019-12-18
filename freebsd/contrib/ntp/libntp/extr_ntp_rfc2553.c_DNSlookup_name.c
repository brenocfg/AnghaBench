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
struct hostent {int dummy; } ;

/* Variables and functions */
 struct hostent* gethostbyname (char const*) ; 
 int h_errno ; 

int
DNSlookup_name(
	const char *name,
	int ai_family,
	struct hostent **Addresses
)
{
	*Addresses = gethostbyname(name);
	return (h_errno);
}