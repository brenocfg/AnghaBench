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

/* Variables and functions */
 unsigned int NEG_ACCEPTED ; 
 unsigned int NEG_ENABLED ; 
 unsigned int NEG_HISMASK ; 
 unsigned int NEG_MYMASK ; 

__attribute__((used)) static const char *
ident_cmd(const char *cmd, unsigned *keep, unsigned *add)
{
  const char *result;

  switch (*cmd) {
    case 'A':
    case 'a':
      result = "accept";
      *keep = NEG_MYMASK;
      *add = NEG_ACCEPTED;
      break;
    case 'D':
    case 'd':
      switch (cmd[1]) {
        case 'E':
        case 'e':
          result = "deny";
          *keep = NEG_MYMASK;
          *add = 0;
          break;
        case 'I':
        case 'i':
          result = "disable";
          *keep = NEG_HISMASK;
          *add = 0;
          break;
        default:
          return NULL;
      }
      break;
    case 'E':
    case 'e':
      result = "enable";
      *keep = NEG_HISMASK;
      *add = NEG_ENABLED;
      break;
    default:
      return NULL;
  }

  return result;
}