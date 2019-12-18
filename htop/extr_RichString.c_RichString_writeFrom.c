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
struct TYPE_4__ {char* chptr; } ;
typedef  TYPE_1__ RichString ;

/* Variables and functions */
 int /*<<< orphan*/  RichString_setLen (TYPE_1__*,int) ; 

__attribute__((used)) static inline void RichString_writeFrom(RichString* this, int attrs, const char* data_c, int from, int len) {
   int newLen = from + len;
   RichString_setLen(this, newLen);
   for (int i = from, j = 0; i < newLen; i++, j++)
      this->chptr[i] = (data_c[j] >= 32 ? data_c[j] : '?') | attrs;
   this->chptr[newLen] = 0;
}