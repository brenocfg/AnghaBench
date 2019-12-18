#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  h64 ;
typedef  int /*<<< orphan*/  h32 ;
typedef  int algoType ;
typedef  int /*<<< orphan*/  XXH64_state_t ;
typedef  int /*<<< orphan*/  XXH32_state_t ;
typedef  int /*<<< orphan*/  U64 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  XXH32_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH32_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH32_update (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  XXH64_digest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  XXHSUM32_DEFAULT_SEED ; 
 int /*<<< orphan*/  XXHSUM64_DEFAULT_SEED ; 
#define  algo_xxh32 129 
#define  algo_xxh64 128 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void BMK_hashStream(void* xxhHashValue, const algoType hashType, FILE* inFile, void* buffer, size_t blockSize)
{
    XXH64_state_t state64;
    XXH32_state_t state32;
    size_t readSize;

    /* Init */
    XXH32_reset(&state32, XXHSUM32_DEFAULT_SEED);
    XXH64_reset(&state64, XXHSUM64_DEFAULT_SEED);

    /* Load file & update hash */
    readSize = 1;
    while (readSize) {
        readSize = fread(buffer, 1, blockSize, inFile);
        switch(hashType)
        {
        case algo_xxh32:
            XXH32_update(&state32, buffer, readSize);
            break;
        case algo_xxh64:
            XXH64_update(&state64, buffer, readSize);
            break;
        default:
            break;
        }
    }

    switch(hashType)
    {
    case algo_xxh32:
        {   U32 const h32 = XXH32_digest(&state32);
            memcpy(xxhHashValue, &h32, sizeof(h32));
            break;
        }
    case algo_xxh64:
        {   U64 const h64 = XXH64_digest(&state64);
            memcpy(xxhHashValue, &h64, sizeof(h64));
            break;
        }
    default:
            break;
    }
}