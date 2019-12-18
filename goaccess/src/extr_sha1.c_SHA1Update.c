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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int* count; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Transform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

void
SHA1Update (SHA1_CTX * context, uint8_t * data, unsigned int len)
{
  unsigned int i, j;

  j = (context->count[0] >> 3) & 63;
  if ((context->count[0] += len << 3) < (len << 3))
    context->count[1]++;
  context->count[1] += (len >> 29);
  if ((j + len) > 63) {
    memcpy (&context->buffer[j], data, (i = 64 - j));
    SHA1Transform (context->state, context->buffer);
    for (; i + 63 < len; i += 64) {
      SHA1Transform (context->state, &data[i]);
    }
    j = 0;
  } else
    i = 0;
  memcpy (&context->buffer[j], &data[i], len - i);
}