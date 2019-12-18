#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINTN ;
struct TYPE_8__ {TYPE_2__* ConOut; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* SetMode ) (TYPE_2__*,scalar_t__) ;int /*<<< orphan*/  (* QueryMode ) (TYPE_2__*,scalar_t__,scalar_t__*,scalar_t__*) ;TYPE_1__* Mode; } ;
struct TYPE_6__ {scalar_t__ MaxMode; } ;
typedef  TYPE_2__ SIMPLE_TEXT_OUTPUT_INTERFACE ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 int CMD_OK ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_5__* ST ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int
text_autoresize()
{
	SIMPLE_TEXT_OUTPUT_INTERFACE *conout;
	EFI_STATUS status;
	UINTN i, max_dim, best_mode, cols, rows;

	conout = ST->ConOut;
	max_dim = best_mode = 0;
	for (i = 0; i < conout->Mode->MaxMode; i++) {
		status = conout->QueryMode(conout, i, &cols, &rows);
		if (EFI_ERROR(status))
			continue;
		if (cols * rows > max_dim) {
			max_dim = cols * rows;
			best_mode = i;
		}
	}
	if (max_dim > 0)
		conout->SetMode(conout, best_mode);
	return (CMD_OK);
}