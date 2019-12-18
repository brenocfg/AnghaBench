#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ *** prec; } ;
typedef  TYPE_1__ secp256k1_ecmult_gen_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ECMULT_GEN_PREC_G ; 
 int ECMULT_GEN_PREC_N ; 
 int /*<<< orphan*/  SECP256K1_ECMULT_GEN_CONTEXT_PREALLOCATED_SIZE ; 
 int SECP256K1_GE_STORAGE_CONST_GET (int /*<<< orphan*/ ) ; 
 void* checked_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_error_callback ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_context_build (TYPE_1__*,void**) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_context_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  secp256k1_ecmult_gen_context_init (TYPE_1__*) ; 
 int /*<<< orphan*/ * stderr ; 

int main(int argc, char **argv) {
    secp256k1_ecmult_gen_context ctx;
    void *prealloc, *base;
    int inner;
    int outer;
    FILE* fp;

    (void)argc;
    (void)argv;

    fp = fopen("src/ecmult_static_context.h","w");
    if (fp == NULL) {
        fprintf(stderr, "Could not open src/ecmult_static_context.h for writing!\n");
        return -1;
    }

    fprintf(fp, "#ifndef _SECP256K1_ECMULT_STATIC_CONTEXT_\n");
    fprintf(fp, "#define _SECP256K1_ECMULT_STATIC_CONTEXT_\n");
    fprintf(fp, "#include \"src/group.h\"\n");
    fprintf(fp, "#define SC SECP256K1_GE_STORAGE_CONST\n");
    fprintf(fp, "#if ECMULT_GEN_PREC_N != %d || ECMULT_GEN_PREC_G != %d\n", ECMULT_GEN_PREC_N, ECMULT_GEN_PREC_G);
    fprintf(fp, "   #error configuration mismatch, invalid ECMULT_GEN_PREC_N, ECMULT_GEN_PREC_G. Try deleting ecmult_static_context.h before the build.\n");
    fprintf(fp, "#endif\n");
    fprintf(fp, "static const secp256k1_ge_storage secp256k1_ecmult_static_context[ECMULT_GEN_PREC_N][ECMULT_GEN_PREC_G] = {\n");

    base = checked_malloc(&default_error_callback, SECP256K1_ECMULT_GEN_CONTEXT_PREALLOCATED_SIZE);
    prealloc = base;
    secp256k1_ecmult_gen_context_init(&ctx);
    secp256k1_ecmult_gen_context_build(&ctx, &prealloc);
    for(outer = 0; outer != ECMULT_GEN_PREC_N; outer++) {
        fprintf(fp,"{\n");
        for(inner = 0; inner != ECMULT_GEN_PREC_G; inner++) {
            fprintf(fp,"    SC(%uu, %uu, %uu, %uu, %uu, %uu, %uu, %uu, %uu, %uu, %uu, %uu, %uu, %uu, %uu, %uu)", SECP256K1_GE_STORAGE_CONST_GET((*ctx.prec)[outer][inner]));
            if (inner != ECMULT_GEN_PREC_G - 1) {
                fprintf(fp,",\n");
            } else {
                fprintf(fp,"\n");
            }
        }
        if (outer != ECMULT_GEN_PREC_N - 1) {
            fprintf(fp,"},\n");
        } else {
            fprintf(fp,"}\n");
        }
    }
    fprintf(fp,"};\n");
    secp256k1_ecmult_gen_context_clear(&ctx);
    free(base);

    fprintf(fp, "#undef SC\n");
    fprintf(fp, "#endif\n");
    fclose(fp);

    return 0;
}