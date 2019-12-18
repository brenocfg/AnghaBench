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
struct descr {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 

__attribute__((used)) static const char *
descr_type(struct descr *d)
{
    if (d->type == SOCK_DGRAM)
	return "udp";
    else if (d->type == SOCK_STREAM)
	return "tcp";
    return "unknown";
}