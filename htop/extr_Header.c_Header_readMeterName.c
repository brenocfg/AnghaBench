#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_6__ {int /*<<< orphan*/ ** columns; } ;
struct TYPE_5__ {scalar_t__ param; } ;
typedef  TYPE_1__ Meter ;
typedef  TYPE_2__ Header ;

/* Variables and functions */
 int /*<<< orphan*/  Meter_name (TYPE_1__*) ; 
 scalar_t__ Vector_get (int /*<<< orphan*/ *,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 char* xMalloc (int) ; 
 int /*<<< orphan*/  xSnprintf (char*,int,char*,scalar_t__) ; 

char* Header_readMeterName(Header* this, int i, int column) {
   Vector* meters = this->columns[column];
   Meter* meter = (Meter*) Vector_get(meters, i);

   int nameLen = strlen(Meter_name(meter));
   int len = nameLen + 100;
   char* name = xMalloc(len);
   strncpy(name, Meter_name(meter), nameLen);
   name[nameLen] = '\0';
   if (meter->param)
      xSnprintf(name + nameLen, len - nameLen, "(%d)", meter->param);

   return name;
}