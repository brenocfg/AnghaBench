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
struct TYPE_4__ {scalar_t__ ticklen; } ;
struct TYPE_5__ {scalar_t__ session_id_length; TYPE_1__ ext; int /*<<< orphan*/  not_resumable; } ;
typedef  TYPE_2__ SSL_SESSION ;

/* Variables and functions */

int SSL_SESSION_is_resumable(const SSL_SESSION *s)
{
    /*
     * In the case of EAP-FAST, we can have a pre-shared "ticket" without a
     * session ID.
     */
    return !s->not_resumable
           && (s->session_id_length > 0 || s->ext.ticklen > 0);
}