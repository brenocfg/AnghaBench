#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  len_t ;
struct TYPE_7__ {int /*<<< orphan*/  src_sz; int /*<<< orphan*/  src; int /*<<< orphan*/  positions; } ;
struct TYPE_6__ {scalar_t__ mark_before_sz; scalar_t__ mark_after_sz; int /*<<< orphan*/  delimiter_sz; int /*<<< orphan*/  delimiter; scalar_t__ output_positions; } ;
typedef  TYPE_1__ Options ;
typedef  int /*<<< orphan*/  GlobalData ;
typedef  TYPE_2__ Candidate ;

/* Variables and functions */
 int /*<<< orphan*/  output_positions (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_with_marks (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_result(GlobalData *global, Candidate *c, Options *opts, len_t needle_len) {
    if (opts->output_positions) output_positions(global, c->positions, needle_len);
    if (opts->mark_before_sz > 0 || opts->mark_after_sz > 0) {
        output_with_marks(global, opts, c->src, c->src_sz, c->positions, needle_len);
    } else {
        output_text(global, c->src, c->src_sz);
    }
    output_text(global, opts->delimiter, opts->delimiter_sz);
}