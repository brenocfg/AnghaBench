#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_17__ {int context; int /*<<< orphan*/  (* final ) (TYPE_3__*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  present; } ;
struct TYPE_15__ {TYPE_2__* cert; } ;
struct TYPE_13__ {scalar_t__ meths_count; } ;
struct TYPE_14__ {TYPE_1__ custext; } ;
typedef  TYPE_3__ SSL ;
typedef  TYPE_4__ RAW_EXTENSION ;
typedef  TYPE_5__ EXTENSION_DEFINITION ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_5__*) ; 
 TYPE_5__* ext_defs ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_parse_extension (TYPE_3__*,size_t,int,TYPE_4__*,int /*<<< orphan*/ *,size_t) ; 

int tls_parse_all_extensions(SSL *s, int context, RAW_EXTENSION *exts, X509 *x,
                             size_t chainidx, int fin)
{
    size_t i, numexts = OSSL_NELEM(ext_defs);
    const EXTENSION_DEFINITION *thisexd;

    /* Calculate the number of extensions in the extensions list */
    numexts += s->cert->custext.meths_count;

    /* Parse each extension in turn */
    for (i = 0; i < numexts; i++) {
        if (!tls_parse_extension(s, i, context, exts, x, chainidx)) {
            /* SSLfatal() already called */
            return 0;
        }
    }

    if (fin) {
        /*
         * Finalise all known extensions relevant to this context,
         * whether we have found them or not
         */
        for (i = 0, thisexd = ext_defs; i < OSSL_NELEM(ext_defs);
             i++, thisexd++) {
            if (thisexd->final != NULL && (thisexd->context & context) != 0
                && !thisexd->final(s, context, exts[i].present)) {
                /* SSLfatal() already called */
                return 0;
            }
        }
    }

    return 1;
}