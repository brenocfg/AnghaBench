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
struct TYPE_3__ {int /*<<< orphan*/  EA_ResetInput; int /*<<< orphan*/  EA_EndRegular; int /*<<< orphan*/  EA_GetInput; int /*<<< orphan*/  EA_View; int /*<<< orphan*/  EA_Move; int /*<<< orphan*/  EA_DelayedJump; int /*<<< orphan*/  EA_Jump; int /*<<< orphan*/  EA_SelectWeapon; int /*<<< orphan*/  EA_MoveRight; int /*<<< orphan*/  EA_MoveLeft; int /*<<< orphan*/  EA_MoveBack; int /*<<< orphan*/  EA_MoveForward; int /*<<< orphan*/  EA_MoveDown; int /*<<< orphan*/  EA_MoveUp; int /*<<< orphan*/  EA_Crouch; int /*<<< orphan*/  EA_Respawn; int /*<<< orphan*/  EA_Use; int /*<<< orphan*/  EA_Attack; int /*<<< orphan*/  EA_Talk; int /*<<< orphan*/  EA_Gesture; int /*<<< orphan*/  EA_Action; int /*<<< orphan*/  EA_SayTeam; int /*<<< orphan*/  EA_Say; int /*<<< orphan*/  EA_Command; } ;
typedef  TYPE_1__ ea_export_t ;

/* Variables and functions */
 int /*<<< orphan*/  EA_Action ; 
 int /*<<< orphan*/  EA_Attack ; 
 int /*<<< orphan*/  EA_Command ; 
 int /*<<< orphan*/  EA_Crouch ; 
 int /*<<< orphan*/  EA_DelayedJump ; 
 int /*<<< orphan*/  EA_EndRegular ; 
 int /*<<< orphan*/  EA_Gesture ; 
 int /*<<< orphan*/  EA_GetInput ; 
 int /*<<< orphan*/  EA_Jump ; 
 int /*<<< orphan*/  EA_Move ; 
 int /*<<< orphan*/  EA_MoveBack ; 
 int /*<<< orphan*/  EA_MoveDown ; 
 int /*<<< orphan*/  EA_MoveForward ; 
 int /*<<< orphan*/  EA_MoveLeft ; 
 int /*<<< orphan*/  EA_MoveRight ; 
 int /*<<< orphan*/  EA_MoveUp ; 
 int /*<<< orphan*/  EA_ResetInput ; 
 int /*<<< orphan*/  EA_Respawn ; 
 int /*<<< orphan*/  EA_Say ; 
 int /*<<< orphan*/  EA_SayTeam ; 
 int /*<<< orphan*/  EA_SelectWeapon ; 
 int /*<<< orphan*/  EA_Talk ; 
 int /*<<< orphan*/  EA_Use ; 
 int /*<<< orphan*/  EA_View ; 

__attribute__((used)) static void Init_EA_Export( ea_export_t *ea ) {
	//ClientCommand elementary actions
	ea->EA_Command = EA_Command;
	ea->EA_Say = EA_Say;
	ea->EA_SayTeam = EA_SayTeam;

	ea->EA_Action = EA_Action;
	ea->EA_Gesture = EA_Gesture;
	ea->EA_Talk = EA_Talk;
	ea->EA_Attack = EA_Attack;
	ea->EA_Use = EA_Use;
	ea->EA_Respawn = EA_Respawn;
	ea->EA_Crouch = EA_Crouch;
	ea->EA_MoveUp = EA_MoveUp;
	ea->EA_MoveDown = EA_MoveDown;
	ea->EA_MoveForward = EA_MoveForward;
	ea->EA_MoveBack = EA_MoveBack;
	ea->EA_MoveLeft = EA_MoveLeft;
	ea->EA_MoveRight = EA_MoveRight;

	ea->EA_SelectWeapon = EA_SelectWeapon;
	ea->EA_Jump = EA_Jump;
	ea->EA_DelayedJump = EA_DelayedJump;
	ea->EA_Move = EA_Move;
	ea->EA_View = EA_View;
	ea->EA_GetInput = EA_GetInput;
	ea->EA_EndRegular = EA_EndRegular;
	ea->EA_ResetInput = EA_ResetInput;
}