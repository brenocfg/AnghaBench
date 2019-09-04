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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_4__ {int rlen; struct TYPE_4__** reps; } ;
typedef  TYPE_1__ mrb_irep ;

/* Variables and functions */
 TYPE_1__* read_irep_record_1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_irep*
read_irep_record(mrb_state *mrb, const uint8_t *bin, size_t *len, uint8_t flags)
{
  mrb_irep *irep = read_irep_record_1(mrb, bin, len, flags);
  int i;

  if (irep == NULL) {
    return NULL;
  }

  bin += *len;
  for (i=0; i<irep->rlen; i++) {
    size_t rlen;

    irep->reps[i] = read_irep_record(mrb, bin, &rlen, flags);
    if (irep->reps[i] == NULL) {
      return NULL;
    }
    bin += rlen;
    *len += rlen;
  }
  return irep;
}