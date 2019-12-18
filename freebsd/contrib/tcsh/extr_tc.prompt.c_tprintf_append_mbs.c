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
struct Strbuf {int dummy; } ;
typedef  int Char ;

/* Variables and functions */
 int /*<<< orphan*/  MB_LEN_MAX ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int) ; 
 int /*<<< orphan*/  one_mbtowc (int*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tprintf_append_mbs(struct Strbuf *buf, const char *mbs, Char attributes)
{
    while (*mbs != 0) {
	Char wc;

	mbs += one_mbtowc(&wc, mbs, MB_LEN_MAX);
	Strbuf_append1(buf, wc | attributes);
    }
}