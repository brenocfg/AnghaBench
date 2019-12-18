#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* ch; int start_pos; } ;
struct tr_pattern {scalar_t__ type; int flag_on_heap; char n; struct tr_pattern* next; TYPE_1__ val; void* flag_reverse; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_9__ {int /*<<< orphan*/  nomem_err; } ;
typedef  TYPE_2__ mrb_state ;
typedef  int mrb_int ;
typedef  void* mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 void* FALSE ; 
 int RSTRING_LEN (int /*<<< orphan*/  const) ; 
 char* RSTRING_PTR (int /*<<< orphan*/  const) ; 
 void* TRUE ; 
 scalar_t__ TR_IN_ORDER ; 
 scalar_t__ TR_RANGE ; 
 scalar_t__ TR_UNINITIALIZED ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  mrb_exc_raise (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_malloc_simple (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tr_free_pattern (TYPE_2__*,struct tr_pattern*) ; 

__attribute__((used)) static struct tr_pattern*
tr_parse_pattern(mrb_state *mrb, struct tr_pattern *ret, const mrb_value v_pattern, mrb_bool flag_reverse_enable)
{
  const char *pattern = RSTRING_PTR(v_pattern);
  mrb_int pattern_length = RSTRING_LEN(v_pattern);
  mrb_bool flag_reverse = FALSE;
  struct tr_pattern *pat1;
  mrb_int i = 0;

  if(flag_reverse_enable && pattern_length >= 2 && pattern[0] == '^') {
    flag_reverse = TRUE;
    i++;
  }

  while (i < pattern_length) {
    /* is range pattern ? */
    mrb_bool const ret_uninit = (ret->type == TR_UNINITIALIZED);
    pat1 = ret_uninit
           ? ret
           : (struct tr_pattern*)mrb_malloc_simple(mrb, sizeof(struct tr_pattern));
    if ((i+2) < pattern_length && pattern[i] != '\\' && pattern[i+1] == '-') {
      if (pat1 == NULL && ret) {
      nomem:
        tr_free_pattern(mrb, ret);
        mrb_exc_raise(mrb, mrb_obj_value(mrb->nomem_err));
        return NULL;            /* not reached */
      }
      pat1->type = TR_RANGE;
      pat1->flag_reverse = flag_reverse;
      pat1->flag_on_heap = !ret_uninit;
      pat1->n = pattern[i+2] - pattern[i] + 1;
      pat1->next = NULL;
      pat1->val.ch[0] = pattern[i];
      pat1->val.ch[1] = pattern[i+2];
      i += 3;
    }
    else {
      /* in order pattern. */
      mrb_int start_pos = i++;
      mrb_int len;

      while (i < pattern_length) {
	if ((i+2) < pattern_length && pattern[i] != '\\' && pattern[i+1] == '-')
          break;
	i++;
      }

      len = i - start_pos;
      if (len > UINT16_MAX) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "tr pattern too long (max 65536)");
      }
      if (pat1 == NULL && ret) {
        goto nomem;
      }
      pat1->type = TR_IN_ORDER;
      pat1->flag_reverse = flag_reverse;
      pat1->flag_on_heap = !ret_uninit;
      pat1->n = len;
      pat1->next = NULL;
      pat1->val.start_pos = start_pos;
    }

    if (ret == NULL || ret_uninit) {
      ret = pat1;
    }
    else {
      struct tr_pattern *p = ret;
      while (p->next != NULL) {
        p = p->next;
      }
      p->next = pat1;
    }
  }

  return ret;
}