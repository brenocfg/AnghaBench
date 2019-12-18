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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  FLAG_BYTEORDER_NATIVE ; 
 scalar_t__ MRB_DUMP_ALIGNMENT ; 
 int MRB_DUMP_INVALID_ARGUMENT ; 
 int MRB_DUMP_OK ; 
 int MRB_DUMP_WRITE_FAULT ; 
 int /*<<< orphan*/  dump_bigendian_p (int) ; 
 int dump_flags (int,int /*<<< orphan*/ ) ; 
 int dump_irep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int**,size_t*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,int*) ; 

int
mrb_dump_irep_cfunc(mrb_state *mrb, mrb_irep *irep, uint8_t flags, FILE *fp, const char *initname)
{
  uint8_t *bin = NULL;
  size_t bin_size = 0, bin_idx = 0;
  int result;

  if (fp == NULL || initname == NULL || initname[0] == '\0') {
    return MRB_DUMP_INVALID_ARGUMENT;
  }
  flags = dump_flags(flags, FLAG_BYTEORDER_NATIVE);
  result = dump_irep(mrb, irep, flags, &bin, &bin_size);
  if (result == MRB_DUMP_OK) {
    if (!dump_bigendian_p(flags)) {
      if (fprintf(fp, "/* dumped in little endian order.\n"
                  "   use `mrbc -E` option for big endian CPU. */\n") < 0) {
        mrb_free(mrb, bin);
        return MRB_DUMP_WRITE_FAULT;
      }
    }
    else {
      if (fprintf(fp, "/* dumped in big endian order.\n"
                  "   use `mrbc -e` option for better performance on little endian CPU. */\n") < 0) {
        mrb_free(mrb, bin);
        return MRB_DUMP_WRITE_FAULT;
      }
    }
    if (fprintf(fp, "#include <stdint.h>\n") < 0) { /* for uint8_t under at least Darwin */
      mrb_free(mrb, bin);
      return MRB_DUMP_WRITE_FAULT;
    }
    if (fprintf(fp,
          "extern const uint8_t %s[];\n"
          "const uint8_t\n"
          "#if defined __GNUC__\n"
          "__attribute__((aligned(%u)))\n"
          "#elif defined _MSC_VER\n"
          "__declspec(align(%u))\n"
          "#endif\n"
          "%s[] = {",
          initname,
          (uint16_t)MRB_DUMP_ALIGNMENT, (uint16_t)MRB_DUMP_ALIGNMENT, initname) < 0) {
      mrb_free(mrb, bin);
      return MRB_DUMP_WRITE_FAULT;
    }
    while (bin_idx < bin_size) {
      if (bin_idx % 16 == 0) {
        if (fputs("\n", fp) == EOF) {
          mrb_free(mrb, bin);
          return MRB_DUMP_WRITE_FAULT;
        }
      }
      if (fprintf(fp, "0x%02x,", bin[bin_idx++]) < 0) {
        mrb_free(mrb, bin);
        return MRB_DUMP_WRITE_FAULT;
      }
    }
    if (fputs("\n};\n", fp) == EOF) {
      mrb_free(mrb, bin);
      return MRB_DUMP_WRITE_FAULT;
    }
  }

  mrb_free(mrb, bin);
  return result;
}