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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdr_str (struct strbuf*,char*,char*) ; 

__attribute__((used)) static void hdr_nocache(struct strbuf *hdr)
{
	hdr_str(hdr, "Expires", "Fri, 01 Jan 1980 00:00:00 GMT");
	hdr_str(hdr, "Pragma", "no-cache");
	hdr_str(hdr, "Cache-Control", "no-cache, max-age=0, must-revalidate");
}