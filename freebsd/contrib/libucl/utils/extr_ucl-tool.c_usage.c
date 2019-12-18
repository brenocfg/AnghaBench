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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void usage(const char *name, FILE *out) {
  fprintf(out, "Usage: %s [--help] [-i|--in file] [-o|--out file]\n", name);
  fprintf(out, "    [-s|--schema file] [-f|--format format]\n\n");
  fprintf(out, "  --help   - print this message and exit\n");
  fprintf(out, "  --in     - specify input filename "
          "(default: standard input)\n");
  fprintf(out, "  --out    - specify output filename "
          "(default: standard output)\n");
  fprintf(out, "  --schema - specify schema file for validation\n");
  fprintf(out, "  --format - output format. Options: ucl (default), "
          "json, compact_json, yaml, msgpack\n");
}