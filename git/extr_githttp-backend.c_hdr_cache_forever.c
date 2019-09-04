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
typedef  scalar_t__ timestamp_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdr_date (struct strbuf*,char*,scalar_t__) ; 
 int /*<<< orphan*/  hdr_str (struct strbuf*,char*,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdr_cache_forever(struct strbuf *hdr)
{
	timestamp_t now = time(NULL);
	hdr_date(hdr, "Date", now);
	hdr_date(hdr, "Expires", now + 31536000);
	hdr_str(hdr, "Cache-Control", "public, max-age=31536000");
}