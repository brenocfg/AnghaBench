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
struct uuid {int dummy; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  snprintf_uuid (char*,int,struct uuid*) ; 

int
sbuf_printf_uuid(struct sbuf *sb, struct uuid *uuid)
{
	char buf[38];

	snprintf_uuid(buf, sizeof(buf), uuid);
	return (sbuf_cat(sb, buf));
}