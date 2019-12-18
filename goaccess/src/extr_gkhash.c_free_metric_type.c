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
struct TYPE_3__ {int type; int /*<<< orphan*/  su64; int /*<<< orphan*/  igsl; int /*<<< orphan*/  ss32; int /*<<< orphan*/  si32; int /*<<< orphan*/  iu64; int /*<<< orphan*/  is32; int /*<<< orphan*/  ii32; } ;
typedef  TYPE_1__ GKHashMetric ;

/* Variables and functions */
#define  MTRC_TYPE_IGSL 134 
#define  MTRC_TYPE_II32 133 
#define  MTRC_TYPE_IS32 132 
#define  MTRC_TYPE_IU64 131 
#define  MTRC_TYPE_SI32 130 
#define  MTRC_TYPE_SS32 129 
#define  MTRC_TYPE_SU64 128 
 int /*<<< orphan*/  des_igsl_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_ii32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_is32_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_iu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_si32_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_ss32_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_su64_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_metric_type (GKHashMetric mtrc)
{
  /* Determine the hash structure type */
  switch (mtrc.type) {
  case MTRC_TYPE_II32:
    des_ii32 (mtrc.ii32);
    break;
  case MTRC_TYPE_IS32:
    des_is32_free (mtrc.is32);
    break;
  case MTRC_TYPE_IU64:
    des_iu64 (mtrc.iu64);
    break;
  case MTRC_TYPE_SI32:
    des_si32_free (mtrc.si32);
    break;
  case MTRC_TYPE_SS32:
    des_ss32_free (mtrc.ss32);
    break;
  case MTRC_TYPE_IGSL:
    des_igsl_free (mtrc.igsl);
    break;
  case MTRC_TYPE_SU64:
    des_su64_free (mtrc.su64);
    break;
  }
}