#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * state; } ;
typedef  TYPE_1__ SHA384_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BE_64_TO_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA384_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA384_Pad (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
SHA384_Final(u_int8_t digest[SHA384_DIGEST_LENGTH], SHA384_CTX *context)
{
	SHA384_Pad(context);

	/* If no digest buffer is passed, we don't bother doing this: */
	if (digest != NULL) {
#if BYTE_ORDER == LITTLE_ENDIAN
		int	i;

		/* Convert TO host byte order */
		for (i = 0; i < 6; i++)
			BE_64_TO_8(digest + i * 8, context->state[i]);
#else
		memcpy(digest, context->state, SHA384_DIGEST_LENGTH);
#endif
	}

	/* Zero out state data */
	memset(context, 0, sizeof(*context));
}