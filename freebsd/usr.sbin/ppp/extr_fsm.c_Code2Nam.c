#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 TYPE_1__* FsmCodes ; 

__attribute__((used)) static const char *
Code2Nam(u_int code)
{
  if (code == 0 || code > sizeof FsmCodes / sizeof FsmCodes[0])
    return "Unknown";
  return FsmCodes[code-1].name;
}