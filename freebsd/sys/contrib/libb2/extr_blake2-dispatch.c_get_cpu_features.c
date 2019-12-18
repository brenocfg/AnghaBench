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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  cpu_feature_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVX ; 
 scalar_t__ IsProcessorFeaturePresent (int) ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  SSE2 ; 
 int /*<<< orphan*/  SSE41 ; 
 int /*<<< orphan*/  SSSE3 ; 
 int /*<<< orphan*/  XOP ; 
 int /*<<< orphan*/  cpuid (int*,int*,int*,int*) ; 
 int xgetbv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline cpu_feature_t get_cpu_features( void )
{
#if defined(HAVE_X86)
  static volatile int initialized = 0;
  static cpu_feature_t feature = NONE; // Safe default
  uint32_t eax, ecx, edx, ebx;

  if( initialized )
    return feature;

  eax = 1;
  cpuid( &eax, &ebx, &ecx, &edx );

  if( 1 & ( edx >> 26 ) )
    feature = SSE2;

  if( 1 & ( ecx >> 9 ) )
    feature = SSSE3;

  if( 1 & ( ecx >> 19 ) )
    feature = SSE41;

#if defined(WIN32) /* Work around the fact that Windows <7 does NOT support AVX... */
  if( IsProcessorFeaturePresent(17) ) /* Some environments don't know about PF_XSAVE_ENABLED */
#endif
  {
    /* check for AVX and OSXSAVE bits */
    if( 1 & ( ecx >> 28 ) & (ecx >> 27) ) {
#if !defined(WIN32) /* Already checked for this in WIN32 */
    if( (xgetbv(0) & 6) == 6 ) /* XCR0 */
#endif
      feature = AVX;
    }


    eax = 0x80000001;
    cpuid( &eax, &ebx, &ecx, &edx );

    if( 1 & ( ecx >> 11 ) )
      feature = XOP;
  }

  /* For future architectures */
  /* 
      eax = 7; ecx = 0;
      cpuid(&eax, &ebx, &ecx, &edx);

      if(1&(ebx >> 5))
        feature = AVX2;
  */
  /* fprintf( stderr, "Using %s engine\n", feature_names[feature] ); */
  initialized = 1;
  return feature;
#else
  return NONE;
#endif
}