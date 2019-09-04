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
struct TYPE_2__ {int ptr; } ;
struct list_decoder {int /*<<< orphan*/  k; TYPE_1__ br; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int,int) ; 

__attribute__((used)) static int raw_int32_decode_int (struct list_decoder *dec) {
  int r;
  memcpy (&r, dec->br.ptr, sizeof (int));
  dec->br.ptr += 4;
  dec->k++;
  return r;
}