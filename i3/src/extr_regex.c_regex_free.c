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
struct regex {struct regex* extra; struct regex* regex; struct regex* pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct regex*) ; 

void regex_free(struct regex *regex) {
    if (!regex)
        return;
    FREE(regex->pattern);
    FREE(regex->regex);
    FREE(regex->extra);
    FREE(regex);
}