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
struct st_h2o_logger_t {int dummy; } ;
struct st_duration_stats_t {int dummy; } ;
typedef  int /*<<< orphan*/  h2o_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  duration_stats_free (struct st_duration_stats_t*) ; 
 struct st_duration_stats_t* h2o_context_get_logger_context (int /*<<< orphan*/ *,struct st_h2o_logger_t*) ; 

__attribute__((used)) static void on_context_dispose(struct st_h2o_logger_t *self, h2o_context_t *ctx)
{
    struct st_duration_stats_t *duration_stats;
    duration_stats = h2o_context_get_logger_context(ctx, self);
    duration_stats_free(duration_stats);
}