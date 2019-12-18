#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ use_dictionary; } ;
typedef  TYPE_2__ config_t ;
struct TYPE_11__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {TYPE_1__ dictionary; } ;
typedef  TYPE_3__ buffer_state_t ;
struct TYPE_14__ {int /*<<< orphan*/  fParams; int /*<<< orphan*/  cParams; } ;
typedef  TYPE_4__ ZSTD_parameters ;
typedef  int /*<<< orphan*/  ZSTD_CStream ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;

/* Variables and functions */
 int const CONFIG_NO_LEVEL ; 
 int /*<<< orphan*/  ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/ * ZSTD_createCDict (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/ * ZSTD_createCDict_advanced (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_dct_auto ; 
 int /*<<< orphan*/  ZSTD_defaultCMem ; 
 int /*<<< orphan*/  ZSTD_dlm_byRef ; 
 size_t ZSTD_initCStream (int /*<<< orphan*/ *,int const) ; 
 size_t ZSTD_initCStream_advanced (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__ const,int /*<<< orphan*/ ) ; 
 size_t ZSTD_initCStream_usingCDict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t ZSTD_initCStream_usingCDict_advanced (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ZSTD_initCStream_usingDict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int config_get_level (TYPE_2__ const*) ; 
 TYPE_4__ config_get_zstd_params (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_cstream(
    buffer_state_t* state,
    ZSTD_CStream* zcs,
    config_t const* config,
    int const advanced,
    ZSTD_CDict** cdict)
{
    size_t zret;
    if (advanced) {
        ZSTD_parameters const params = config_get_zstd_params(config, 0, 0);
        ZSTD_CDict* dict = NULL;
        if (cdict) {
            if (!config->use_dictionary)
              return 1;
            *cdict = ZSTD_createCDict_advanced(
                state->dictionary.data,
                state->dictionary.size,
                ZSTD_dlm_byRef,
                ZSTD_dct_auto,
                params.cParams,
                ZSTD_defaultCMem);
            if (!*cdict) {
                return 1;
            }
            zret = ZSTD_initCStream_usingCDict_advanced(
                zcs, *cdict, params.fParams, ZSTD_CONTENTSIZE_UNKNOWN);
        } else {
            zret = ZSTD_initCStream_advanced(
                zcs,
                config->use_dictionary ? state->dictionary.data : NULL,
                config->use_dictionary ? state->dictionary.size : 0,
                params,
                ZSTD_CONTENTSIZE_UNKNOWN);
        }
    } else {
        int const level = config_get_level(config);
        if (level == CONFIG_NO_LEVEL)
            return 1;
        if (cdict) {
            if (!config->use_dictionary)
              return 1;
            *cdict = ZSTD_createCDict(
                state->dictionary.data,
                state->dictionary.size,
                level);
            if (!*cdict) {
                return 1;
            }
            zret = ZSTD_initCStream_usingCDict(zcs, *cdict);
        } else if (config->use_dictionary) {
            zret = ZSTD_initCStream_usingDict(
                zcs,
                state->dictionary.data,
                state->dictionary.size,
                level);
        } else {
            zret = ZSTD_initCStream(zcs, level);
        }
    }
    if (ZSTD_isError(zret)) {
        return 1;
    }
    return 0;
}