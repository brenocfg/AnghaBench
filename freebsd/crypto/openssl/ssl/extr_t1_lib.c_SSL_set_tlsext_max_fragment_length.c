#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {scalar_t__ max_fragment_len_mode; } ;
struct TYPE_5__ {TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MAX_FRAGMENT_LENGTH_EXT_VALID (scalar_t__) ; 
 int /*<<< orphan*/  SSL_F_SSL_SET_TLSEXT_MAX_FRAGMENT_LENGTH ; 
 int /*<<< orphan*/  SSL_R_SSL3_EXT_INVALID_MAX_FRAGMENT_LENGTH ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLSEXT_max_fragment_length_DISABLED ; 

int SSL_set_tlsext_max_fragment_length(SSL *ssl, uint8_t mode)
{
    if (mode != TLSEXT_max_fragment_length_DISABLED
            && !IS_MAX_FRAGMENT_LENGTH_EXT_VALID(mode)) {
        SSLerr(SSL_F_SSL_SET_TLSEXT_MAX_FRAGMENT_LENGTH,
               SSL_R_SSL3_EXT_INVALID_MAX_FRAGMENT_LENGTH);
        return 0;
    }

    ssl->ext.max_fragment_len_mode = mode;
    return 1;
}