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
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALNUM_PUNCT (int /*<<< orphan*/ *,char) ; 
 scalar_t__ IS_ESC (int /*<<< orphan*/ *,char) ; 
 char* scan_esc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static char *eat_alpha_numeric(CONF *conf, char *p)
{
    for (;;) {
        if (IS_ESC(conf, *p)) {
            p = scan_esc(conf, p);
            continue;
        }
        if (!IS_ALNUM_PUNCT(conf, *p))
            return p;
        p++;
    }
}