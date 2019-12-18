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
typedef  scalar_t__ u_short ;
struct TYPE_2__ {scalar_t__ from; scalar_t__ to; char const* name; } ;

/* Variables and functions */
 unsigned int NPROTOCOLS ; 
 TYPE_1__* protocols ; 

const char *
hdlc_Protocol2Nam(u_short proto)
{
  unsigned f;

  for (f = 0; f < NPROTOCOLS; f++)
    if (proto >= protocols[f].from && proto <= protocols[f].to)
      return protocols[f].name;
    else if (proto < protocols[f].from)
      break;
  return "unrecognised protocol";
}