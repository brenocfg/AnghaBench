#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_vprint_func ;
struct TYPE_3__ {int length; scalar_t__ data; } ;
typedef  TYPE_1__ heim_bit_string ;

/* Variables and functions */
 int /*<<< orphan*/  print_func (int /*<<< orphan*/ ,void*,char*,unsigned char,...) ; 

void
hx509_bitstring_print(const heim_bit_string *b,
		      hx509_vprint_func func, void *ctx)
{
    size_t i;
    print_func(func, ctx, "\tlength: %d\n\t", b->length);
    for (i = 0; i < (b->length + 7) / 8; i++)
	print_func(func, ctx, "%02x%s%s",
		   ((unsigned char *)b->data)[i],
		   i < (b->length - 7) / 8
		   && (i == 0 || (i % 16) != 15) ? ":" : "",
		   i != 0 && (i % 16) == 15 ?
		   (i <= ((b->length + 7) / 8 - 2) ? "\n\t" : "\n"):"");
}