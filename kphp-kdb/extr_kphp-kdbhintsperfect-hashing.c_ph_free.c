#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  d; int /*<<< orphan*/  sums; int /*<<< orphan*/  used; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ perfect_hash ;

/* Variables and functions */
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_code_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_sums_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_used_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ph_init (TYPE_1__*) ; 

void ph_free (perfect_hash *h) {
  dl_free (h->code, get_code_len (h->d));
  dl_free (h->used, get_used_len (h->d));
  dl_free (h->sums, get_sums_len (h->d));
  ph_init (h);
}