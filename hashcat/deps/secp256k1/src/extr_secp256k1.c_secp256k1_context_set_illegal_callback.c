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
struct TYPE_5__ {void (* fn ) (char const*,void*) ;void const* data; } ;
struct TYPE_6__ {TYPE_1__ illegal_callback; } ;
typedef  TYPE_2__ secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_CHECK_NO_RETURN (int) ; 
 TYPE_2__* secp256k1_context_no_precomp ; 
 void secp256k1_default_illegal_callback_fn (char const*,void*) ; 

void secp256k1_context_set_illegal_callback(secp256k1_context* ctx, void (*fun)(const char* message, void* data), const void* data) {
    ARG_CHECK_NO_RETURN(ctx != secp256k1_context_no_precomp);
    if (fun == NULL) {
        fun = secp256k1_default_illegal_callback_fn;
    }
    ctx->illegal_callback.fn = fun;
    ctx->illegal_callback.data = data;
}