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
typedef  TYPE_1__ SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BE_32_TO_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA256_Pad (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
SHA256_Final(u_int8_t digest[SHA256_DIGEST_LENGTH], SHA256_CTX *context)
{
	SHA256_Pad(context);

	/* If no digest buffer is passed, we don't bother doing this: */
	if (digest != NULL) {
#if BYTE_ORDER == LITTLE_ENDIAN
		int	i;

		/* Convert TO host byte order */
		for (i = 0; i < 8; i++)
			BE_32_TO_8(digest + i * 4, context->state[i]);
#else
		memcpy(digest, context->state, SHA256_DIGEST_LENGTH);
#endif
		memset(context, 0, sizeof(*context));
	}
}