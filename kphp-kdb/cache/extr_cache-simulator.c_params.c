#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  default_file_size; int /*<<< orphan*/  download_speed; int /*<<< orphan*/  disk_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_PARAM_I32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_PARAM_I64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_PARAM_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amortization_counters_initialization_string ; 
 int /*<<< orphan*/  delay_between_priority_lists_requests ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  human_readable_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_using_greedy_strategy ; 
 int /*<<< orphan*/  optimization ; 
 TYPE_1__ simulation_params ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void params (void) {
  fprintf (stderr, "disk_size\t%lld(%s)\n", simulation_params.disk_size, human_readable_size (simulation_params.disk_size));
  fprintf (stderr, "download_speed\t%lld(%s/sec)\n", simulation_params.download_speed, human_readable_size (simulation_params.download_speed));
  PRINT_PARAM_I64(delay_between_priority_lists_requests);
  fprintf (stderr, "default_file_size\t%lld(%s)\n", simulation_params.default_file_size, human_readable_size (simulation_params.default_file_size));
  PRINT_PARAM_I32(init_using_greedy_strategy);
  PRINT_PARAM_STR(amortization_counters_initialization_string);
  PRINT_PARAM_I32(optimization);
  fflush (stderr);
}