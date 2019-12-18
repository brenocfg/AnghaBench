#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* vec4_t ;
struct TYPE_11__ {void* color; } ;
struct TYPE_10__ {void* color; } ;
struct TYPE_9__ {void* color; } ;
struct TYPE_8__ {void* color; } ;
struct TYPE_7__ {void* color; } ;
struct TYPE_12__ {TYPE_5__ item_nightmare; TYPE_4__ item_hard; TYPE_3__ item_medium; TYPE_2__ item_easy; TYPE_1__ item_baby; } ;

/* Variables and functions */
 TYPE_6__ skillMenuInfo ; 

__attribute__((used)) static void SetSkillColor( int skill, vec4_t color ) {
	switch( skill ) {
	case 1:
		skillMenuInfo.item_baby.color = color;
		break;
	case 2:
		skillMenuInfo.item_easy.color = color;
		break;
	case 3:
		skillMenuInfo.item_medium.color = color;
		break;
	case 4:
		skillMenuInfo.item_hard.color = color;
		break;
	case 5:
		skillMenuInfo.item_nightmare.color = color;
		break;
	default:
		break;
	}
}