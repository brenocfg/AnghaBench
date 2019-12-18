#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bktr_chnlset {size_t index; int /*<<< orphan*/  max_channel; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ptr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_MAX_CHNLSET_NAME_LEN ; 
 size_t CHNLSET_MAX ; 
 size_t CHNLSET_MIN ; 
 int EINVAL ; 
 TYPE_1__* freqTable ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
tuner_getchnlset(struct bktr_chnlset *chnlset)
{
       if (( chnlset->index < CHNLSET_MIN ) ||
               ( chnlset->index > CHNLSET_MAX ))
                       return( EINVAL );

       memcpy(&chnlset->name, &freqTable[chnlset->index].name,
               BT848_MAX_CHNLSET_NAME_LEN);

       chnlset->max_channel=freqTable[chnlset->index].ptr[0];
       return( 0 );
}