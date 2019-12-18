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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ are_names_bad () ; 
 int /*<<< orphan*/  data_finish () ; 
 int data_init (int /*<<< orphan*/ ) ; 
 int diff_results (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  g_cache ; 
 scalar_t__ g_diff ; 
 int /*<<< orphan*/  g_output ; 
 int /*<<< orphan*/  g_zstdcli ; 
 int /*<<< orphan*/  method_set_zstdcli (int /*<<< orphan*/ ) ; 
 int parse_args (int,char**) ; 
 int run_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

int main(int argc, char** argv) {
    /* Parse args and validate modules. */
    int ret = parse_args(argc, argv);
    if (ret != 0)
        return ret;

    if (are_names_bad())
        return 1;

    /* Initialize modules. */
    method_set_zstdcli(g_zstdcli);
    ret = data_init(g_cache);
    if (ret != 0) {
        fprintf(stderr, "data_init() failed with error=%s\n", strerror(ret));
        return 1;
    }

    /* Run the regression tests. */
    ret = 1;
    FILE* results = fopen(g_output, "w");
    if (results == NULL) {
        fprintf(stderr, "Failed to open the output file\n");
        goto out;
    }
    ret = run_all(results);
    fclose(results);

    if (ret != 0)
        goto out;

    if (g_diff)
        /* Diff the new results with the previous results. */
        ret = diff_results(g_output, g_diff);

out:
    data_finish();
    return ret;
}