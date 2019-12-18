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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/ * d2i_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,long) ; 

__attribute__((used)) static X509 *to_x509(ptls_iovec_t vec)
{
    const uint8_t *p = vec.base;
    return d2i_X509(NULL, &p, (long)vec.len);
}