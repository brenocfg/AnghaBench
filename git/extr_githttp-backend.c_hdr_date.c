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
typedef  int /*<<< orphan*/  timestamp_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFC2822 ; 
 int /*<<< orphan*/  hdr_str (struct strbuf*,char const*,char const*) ; 
 char* show_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdr_date(struct strbuf *hdr, const char *name, timestamp_t when)
{
	const char *value = show_date(when, 0, DATE_MODE(RFC2822));
	hdr_str(hdr, name, value);
}