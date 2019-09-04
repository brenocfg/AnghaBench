#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* hashes; } ;
typedef  TYPE_3__ ptls_key_schedule_t ;
struct TYPE_7__ {TYPE_1__* algo; } ;
struct TYPE_6__ {int /*<<< orphan*/  empty_digest; } ;

/* Variables and functions */
 int derive_secret_with_hash (TYPE_3__*,void*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int derive_secret_with_empty_digest(ptls_key_schedule_t *sched, void *secret, const char *label)
{
    return derive_secret_with_hash(sched, secret, label, sched->hashes[0].algo->empty_digest);
}