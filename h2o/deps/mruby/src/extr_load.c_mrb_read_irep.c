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

/* Variables and functions */
 int /*<<< orphan*/  FLAG_SRC_MALLOC ; 
 int /*<<< orphan*/  FLAG_SRC_STATIC ; 
 scalar_t__ mrb_ro_data_p (char*) ; 
 int /*<<< orphan*/ * read_irep (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

mrb_irep*
mrb_read_irep(mrb_state *mrb, const uint8_t *bin)
{
#ifdef MRB_USE_ETEXT_EDATA
  uint8_t flags = mrb_ro_data_p((char*)bin) ? FLAG_SRC_STATIC : FLAG_SRC_MALLOC;
#else
  uint8_t flags = FLAG_SRC_STATIC;
#endif

  return read_irep(mrb, bin, flags);
}