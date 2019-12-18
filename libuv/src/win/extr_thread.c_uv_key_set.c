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
struct TYPE_3__ {int /*<<< orphan*/  tls_index; } ;
typedef  TYPE_1__ uv_key_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TlsSetValue (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  abort () ; 

void uv_key_set(uv_key_t* key, void* value) {
  if (TlsSetValue(key->tls_index, value) == FALSE)
    abort();
}