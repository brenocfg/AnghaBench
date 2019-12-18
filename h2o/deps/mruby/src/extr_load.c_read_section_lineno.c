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
struct rite_section_lineno_header {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;

/* Variables and functions */
 int read_lineno_record (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
read_section_lineno(mrb_state *mrb, const uint8_t *bin, mrb_irep *irep)
{
  size_t len;

  len = 0;
  bin += sizeof(struct rite_section_lineno_header);

  /* Read Binary Data Section */
  return read_lineno_record(mrb, bin, irep, &len);
}