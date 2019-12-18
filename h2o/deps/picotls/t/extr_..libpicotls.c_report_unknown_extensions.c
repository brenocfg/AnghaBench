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
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_raw_extension_t ;
struct TYPE_4__ {int (* collected_extensions ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * collect_extension; } ;
typedef  TYPE_1__ ptls_handshake_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int report_unknown_extensions(ptls_t *tls, ptls_handshake_properties_t *properties, ptls_raw_extension_t *slots)
{
    if (properties != NULL && properties->collect_extension != NULL) {
        assert(properties->collected_extensions != NULL);
        return properties->collected_extensions(tls, properties, slots);
    } else {
        return 0;
    }
}