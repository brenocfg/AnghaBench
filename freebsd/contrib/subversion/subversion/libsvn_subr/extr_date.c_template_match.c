#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int svn_boolean_t ;
struct TYPE_7__ {char const* valid; int offset; int action; } ;
typedef  TYPE_1__ rule ;
typedef  int /*<<< orphan*/  ms ;
struct TYPE_9__ {int tm_gmtoff; } ;
struct TYPE_8__ {int offhours; int offminutes; TYPE_3__ base; } ;
typedef  TYPE_2__ match_state ;
typedef  TYPE_3__ apr_time_exp_t ;
typedef  int apr_int32_t ;

/* Variables and functions */
#define  ACCEPT 134 
#define  ACCUM 133 
 int FALSE ; 
#define  MICRO 132 
#define  NOOP 131 
#define  SKIP 130 
#define  SKIPFROM 129 
 int TRUE ; 
#define  TZIND 128 
 TYPE_1__* find_rule (char const) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static svn_boolean_t
template_match(apr_time_exp_t *expt, svn_boolean_t *localtz,
               const char *template, const char *value)
{
  int multiplier = 100000;
  int tzind = 0;
  match_state ms;
  char *base = (char *)&ms;

  memset(&ms, 0, sizeof(ms));

  for (;;)
    {
      const rule *match = find_rule(*template++);
      char vchar = *value++;
      apr_int32_t *place;

      if (!match || (match->valid
                     && (!vchar || !strchr(match->valid, vchar))))
        return FALSE;

      /* Compute the address of memory location affected by this
         rule by adding match->offset bytes to the address of ms.
         Because this is a byte-quantity, it is necessary to cast
         &ms to char *. */
      place = (apr_int32_t *)(base + match->offset);
      switch (match->action)
        {
        case ACCUM:
          *place = *place * 10 + vchar - '0';
          continue;
        case MICRO:
          *place += (vchar - '0') * multiplier;
          multiplier /= 10;
          continue;
        case TZIND:
          tzind = vchar;
          continue;
        case SKIP:
          value--;
          continue;
        case NOOP:
          continue;
        case SKIPFROM:
          if (!vchar)
            break;
          match = find_rule(*template);
          if (!strchr(match->valid, vchar))
            template = strchr(template, ']') + 1;
          value--;
          continue;
        case ACCEPT:
          if (vchar)
            return FALSE;
          break;
        }

      break;
    }

  /* Validate gmt offset here, since we can't reliably do it later. */
  if (ms.offhours > 23 || ms.offminutes > 59)
    return FALSE;

  /* tzind will be '+' or '-' for an explicit time zone, 'Z' to
     indicate UTC, or 0 to indicate local time. */
  switch (tzind)
    {
    case '+':
      ms.base.tm_gmtoff = ms.offhours * 3600 + ms.offminutes * 60;
      break;
    case '-':
      ms.base.tm_gmtoff = -(ms.offhours * 3600 + ms.offminutes * 60);
      break;
    }

  *expt = ms.base;
  *localtz = (tzind == 0);
  return TRUE;
}