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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  kernel_rule_t ;

/* Variables and functions */
 scalar_t__ MAX_KERNEL_RULES ; 
#define  RULE_OP_MANGLE_APPEND 169 
#define  RULE_OP_MANGLE_CHR_DECR 168 
#define  RULE_OP_MANGLE_CHR_INCR 167 
#define  RULE_OP_MANGLE_CHR_SHIFTL 166 
#define  RULE_OP_MANGLE_CHR_SHIFTR 165 
#define  RULE_OP_MANGLE_DELETE_AT 164 
#define  RULE_OP_MANGLE_DELETE_FIRST 163 
#define  RULE_OP_MANGLE_DELETE_LAST 162 
#define  RULE_OP_MANGLE_DUPEBLOCK_FIRST 161 
#define  RULE_OP_MANGLE_DUPEBLOCK_LAST 160 
#define  RULE_OP_MANGLE_DUPECHAR_ALL 159 
#define  RULE_OP_MANGLE_DUPECHAR_FIRST 158 
#define  RULE_OP_MANGLE_DUPECHAR_LAST 157 
#define  RULE_OP_MANGLE_DUPEWORD 156 
#define  RULE_OP_MANGLE_DUPEWORD_TIMES 155 
#define  RULE_OP_MANGLE_EXTRACT 154 
#define  RULE_OP_MANGLE_INSERT 153 
#define  RULE_OP_MANGLE_LREST 152 
#define  RULE_OP_MANGLE_LREST_UFIRST 151 
#define  RULE_OP_MANGLE_NOOP 150 
#define  RULE_OP_MANGLE_OMIT 149 
#define  RULE_OP_MANGLE_OVERSTRIKE 148 
#define  RULE_OP_MANGLE_PREPEND 147 
#define  RULE_OP_MANGLE_PURGECHAR 146 
#define  RULE_OP_MANGLE_REFLECT 145 
#define  RULE_OP_MANGLE_REPLACE 144 
#define  RULE_OP_MANGLE_REPLACE_NM1 143 
#define  RULE_OP_MANGLE_REPLACE_NP1 142 
#define  RULE_OP_MANGLE_REVERSE 141 
#define  RULE_OP_MANGLE_ROTATE_LEFT 140 
#define  RULE_OP_MANGLE_ROTATE_RIGHT 139 
#define  RULE_OP_MANGLE_SWITCH_AT 138 
#define  RULE_OP_MANGLE_SWITCH_FIRST 137 
#define  RULE_OP_MANGLE_SWITCH_LAST 136 
#define  RULE_OP_MANGLE_TITLE 135 
#define  RULE_OP_MANGLE_TITLE_SEP 134 
#define  RULE_OP_MANGLE_TOGGLECASE_REC 133 
#define  RULE_OP_MANGLE_TOGGLE_AT 132 
#define  RULE_OP_MANGLE_TREST 131 
#define  RULE_OP_MANGLE_TRUNCATE_AT 130 
#define  RULE_OP_MANGLE_UREST 129 
#define  RULE_OP_MANGLE_UREST_LFIRST 128 
 int /*<<< orphan*/  SET_NAME (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  SET_P0 (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  SET_P0_CONV (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  SET_P1 (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  SET_P1_CONV (int /*<<< orphan*/ *,char) ; 

int cpu_rule_to_kernel_rule (char *rule_buf, u32 rule_len, kernel_rule_t *rule)
{
  u32 rule_pos;
  u32 rule_cnt;

  for (rule_pos = 0, rule_cnt = 0; rule_pos < rule_len && rule_cnt < MAX_KERNEL_RULES; rule_pos++, rule_cnt++)
  {
    switch (rule_buf[rule_pos])
    {
      case ' ':
        rule_cnt--;
        break;

      case RULE_OP_MANGLE_NOOP:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_LREST:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_UREST:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_LREST_UFIRST:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_UREST_LFIRST:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_TREST:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_TOGGLE_AT:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_REVERSE:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_DUPEWORD:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_DUPEWORD_TIMES:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_REFLECT:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_ROTATE_LEFT:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_ROTATE_RIGHT:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_APPEND:
        SET_NAME (rule, rule_buf[rule_pos]);
        SET_P0   (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_PREPEND:
        SET_NAME (rule, rule_buf[rule_pos]);
        SET_P0   (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_DELETE_FIRST:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_DELETE_LAST:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_DELETE_AT:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_EXTRACT:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        SET_P1_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_OMIT:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        SET_P1_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_INSERT:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        SET_P1      (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_OVERSTRIKE:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        SET_P1      (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_TRUNCATE_AT:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_REPLACE:
        SET_NAME (rule, rule_buf[rule_pos]);
        SET_P0   (rule, rule_buf[rule_pos]);
        SET_P1   (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_PURGECHAR:
        SET_NAME (rule, rule_buf[rule_pos]);
        SET_P0   (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_TOGGLECASE_REC:
        return -1;

      case RULE_OP_MANGLE_DUPECHAR_FIRST:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_DUPECHAR_LAST:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_DUPECHAR_ALL:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_SWITCH_FIRST:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_SWITCH_LAST:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_SWITCH_AT:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        SET_P1_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_CHR_SHIFTL:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_CHR_SHIFTR:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_CHR_INCR:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_CHR_DECR:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_REPLACE_NP1:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_REPLACE_NM1:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_DUPEBLOCK_FIRST:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_DUPEBLOCK_LAST:
        SET_NAME    (rule, rule_buf[rule_pos]);
        SET_P0_CONV (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_TITLE:
        SET_NAME (rule, rule_buf[rule_pos]);
        break;

      case RULE_OP_MANGLE_TITLE_SEP:
        SET_NAME (rule, rule_buf[rule_pos]);
        SET_P0   (rule, rule_buf[rule_pos]);
        break;

      default:
        return -1;
    }
  }

  if (rule_pos < rule_len) return -1;

  return 0;
}