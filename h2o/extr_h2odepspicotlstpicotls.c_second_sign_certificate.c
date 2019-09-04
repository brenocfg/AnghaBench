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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_sign_certificate_t ;
typedef  int /*<<< orphan*/  ptls_iovec_t ;
typedef  int /*<<< orphan*/  ptls_buffer_t ;
struct TYPE_3__ {int (* cb ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  sc_callcnt ; 
 TYPE_1__* second_sc_orig ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int second_sign_certificate(ptls_sign_certificate_t *self, ptls_t *tls, uint16_t *selected_algorithm, ptls_buffer_t *output,
                                   ptls_iovec_t input, const uint16_t *algorithms, size_t num_algorithms)
{
    ++sc_callcnt;
    return second_sc_orig->cb(second_sc_orig, tls, selected_algorithm, output, input, algorithms, num_algorithms);
}