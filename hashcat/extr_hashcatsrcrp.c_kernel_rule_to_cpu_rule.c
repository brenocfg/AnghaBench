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
 int /*<<< orphan*/  GET_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_P0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_P0_CONV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_P1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_P1_CONV (int /*<<< orphan*/ *) ; 
 scalar_t__ HCBUFSIZ_LARGE ; 
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

int kernel_rule_to_cpu_rule (char *rule_buf, kernel_rule_t *rule)
{
  u32 rule_cnt;
  u32 rule_pos;
  u32 rule_len = HCBUFSIZ_LARGE - 1; // maximum possible len

  for (rule_cnt = 0, rule_pos = 0; rule_pos < rule_len && rule_cnt < MAX_KERNEL_RULES; rule_pos++, rule_cnt++)
  {
    char rule_cmd;

    GET_NAME (rule);

    if (rule_cnt > 0) rule_buf[rule_pos++] = ' ';

    switch (rule_cmd)
    {
      case RULE_OP_MANGLE_NOOP:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_LREST:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_UREST:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_LREST_UFIRST:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_UREST_LFIRST:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_TREST:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_TOGGLE_AT:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_REVERSE:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_DUPEWORD:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_DUPEWORD_TIMES:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_REFLECT:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_ROTATE_LEFT:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_ROTATE_RIGHT:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_APPEND:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0 (rule);
        break;

      case RULE_OP_MANGLE_PREPEND:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0 (rule);
        break;

      case RULE_OP_MANGLE_DELETE_FIRST:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_DELETE_LAST:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_DELETE_AT:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_EXTRACT:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        GET_P1_CONV (rule);
        break;

      case RULE_OP_MANGLE_OMIT:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        GET_P1_CONV (rule);
        break;

      case RULE_OP_MANGLE_INSERT:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        GET_P1      (rule);
        break;

      case RULE_OP_MANGLE_OVERSTRIKE:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        GET_P1      (rule);
        break;

      case RULE_OP_MANGLE_TRUNCATE_AT:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_REPLACE:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0 (rule);
        GET_P1 (rule);
        break;

      case RULE_OP_MANGLE_PURGECHAR:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0 (rule);
        break;

      case RULE_OP_MANGLE_TOGGLECASE_REC:
        return -1;

      case RULE_OP_MANGLE_DUPECHAR_FIRST:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_DUPECHAR_LAST:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_DUPECHAR_ALL:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_SWITCH_FIRST:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_SWITCH_LAST:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_SWITCH_AT:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        GET_P1_CONV (rule);
        break;

      case RULE_OP_MANGLE_CHR_SHIFTL:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_CHR_SHIFTR:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_CHR_INCR:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_CHR_DECR:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_REPLACE_NP1:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_REPLACE_NM1:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_DUPEBLOCK_FIRST:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_DUPEBLOCK_LAST:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0_CONV (rule);
        break;

      case RULE_OP_MANGLE_TITLE:
        rule_buf[rule_pos] = rule_cmd;
        break;

      case RULE_OP_MANGLE_TITLE_SEP:
        rule_buf[rule_pos] = rule_cmd;
        GET_P0 (rule);
        break;

      case 0:
        if (rule_pos == 0) return -1;
        return rule_pos - 1;

      default:
        return -1;
    }
  }

  return rule_pos;
}