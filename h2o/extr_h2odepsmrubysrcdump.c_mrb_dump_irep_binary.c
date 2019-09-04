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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  int /*<<< orphan*/  bin ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_BYTEORDER_NONATIVE ; 
 int MRB_DUMP_INVALID_ARGUMENT ; 
 int MRB_DUMP_OK ; 
 int MRB_DUMP_WRITE_FAULT ; 
 int /*<<< orphan*/  dump_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dump_irep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 size_t fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
mrb_dump_irep_binary(mrb_state *mrb, mrb_irep *irep, uint8_t flags, FILE* fp)
{
  uint8_t *bin = NULL;
  size_t bin_size = 0;
  int result;

  if (fp == NULL) {
    return MRB_DUMP_INVALID_ARGUMENT;
  }

  result = dump_irep(mrb, irep, dump_flags(flags, FLAG_BYTEORDER_NONATIVE), &bin, &bin_size);
  if (result == MRB_DUMP_OK) {
    if (fwrite(bin, sizeof(bin[0]), bin_size, fp) != bin_size) {
      result = MRB_DUMP_WRITE_FAULT;
    }
  }

  mrb_free(mrb, bin);
  return result;
}