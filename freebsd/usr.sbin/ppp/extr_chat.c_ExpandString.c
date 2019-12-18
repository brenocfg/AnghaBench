#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct chat {TYPE_5__* physical; int /*<<< orphan*/  phone; } ;
struct TYPE_10__ {TYPE_4__* dl; } ;
struct TYPE_9__ {TYPE_3__* bundle; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  key; } ;
struct TYPE_7__ {TYPE_1__ auth; } ;
struct TYPE_8__ {TYPE_2__ cfg; } ;

/* Variables and functions */
 int SECTICKS ; 
 int /*<<< orphan*/  chat_Pause (struct chat*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ExpandString(struct chat *c, const char *str, char *result, int reslen, int cr)
{
  int len;

  result[--reslen] = '\0';
  while (*str && reslen > 0) {
    switch (*str) {
    case '\\':
      str++;
      switch (*str) {
      case 'c':
	cr = 0;
	break;
      case 'd':		/* Delay 2 seconds */
        chat_Pause(c, 2 * SECTICKS);
	break;
      case 'p':
        chat_Pause(c, SECTICKS / 4);
	break;		/* Delay 0.25 seconds */
      case 'n':
	*result++ = '\n';
	reslen--;
	break;
      case 'r':
	*result++ = '\r';
	reslen--;
	break;
      case 's':
	*result++ = ' ';
	reslen--;
	break;
      case 't':
	*result++ = '\t';
	reslen--;
	break;
      case 'P':
	strncpy(result, c->physical->dl->bundle->cfg.auth.key, reslen);
        len = strlen(result);
	reslen -= len;
	result += len;
	break;
      case 'T':
        if (c->phone) {
          strncpy(result, c->phone, reslen);
          len = strlen(result);
          reslen -= len;
          result += len;
        }
	break;
      case 'U':
	strncpy(result, c->physical->dl->bundle->cfg.auth.name, reslen);
        len = strlen(result);
	reslen -= len;
	result += len;
	break;
      default:
	reslen--;
	*result++ = *str;
	break;
      }
      if (*str)
	str++;
      break;
    case '^':
      str++;
      if (*str) {
	*result++ = *str++ & 0x1f;
	reslen--;
      }
      break;
    default:
      *result++ = *str++;
      reslen--;
      break;
    }
  }
  if (--reslen > 0) {
    if (cr)
      *result++ = '\r';
  }
  if (--reslen > 0)
    *result++ = '\0';
  return (result);
}