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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  context ;
struct TYPE_4__ {void* h4; void* h3; void* h2; void* h1; void* h0; void** h; } ;
typedef  TYPE_1__ SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_Transform (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sha1_transform(u32 *state, const u8 data[64])
{
	SHA_CTX context;
	os_memset(&context, 0, sizeof(context));
#if defined(OPENSSL_IS_BORINGSSL) && !defined(ANDROID)
	context.h[0] = state[0];
	context.h[1] = state[1];
	context.h[2] = state[2];
	context.h[3] = state[3];
	context.h[4] = state[4];
	SHA1_Transform(&context, data);
	state[0] = context.h[0];
	state[1] = context.h[1];
	state[2] = context.h[2];
	state[3] = context.h[3];
	state[4] = context.h[4];
#else
	context.h0 = state[0];
	context.h1 = state[1];
	context.h2 = state[2];
	context.h3 = state[3];
	context.h4 = state[4];
	SHA1_Transform(&context, data);
	state[0] = context.h0;
	state[1] = context.h1;
	state[2] = context.h2;
	state[3] = context.h3;
	state[4] = context.h4;
#endif
}