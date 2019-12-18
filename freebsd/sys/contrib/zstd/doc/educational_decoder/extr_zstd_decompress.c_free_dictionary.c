#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* const content; int /*<<< orphan*/  ml_dtable; int /*<<< orphan*/  of_dtable; int /*<<< orphan*/  ll_dtable; int /*<<< orphan*/  literals_dtable; } ;
typedef  TYPE_1__ dictionary_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSE_free_dtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HUF_free_dtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__* const) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

void free_dictionary(dictionary_t *const dict) {
    HUF_free_dtable(&dict->literals_dtable);
    FSE_free_dtable(&dict->ll_dtable);
    FSE_free_dtable(&dict->of_dtable);
    FSE_free_dtable(&dict->ml_dtable);

    free(dict->content);

    memset(dict, 0, sizeof(dictionary_t));

    free(dict);
}