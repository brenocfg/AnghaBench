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
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 struct hostent* cap_gethostbyname2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

struct hostent *
cap_gethostbyname(cap_channel_t *chan, const char *name)
{

	return (cap_gethostbyname2(chan, name, AF_INET));
}