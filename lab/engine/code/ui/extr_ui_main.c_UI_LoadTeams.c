__attribute__((used)) static void UI_LoadTeams( void ) {
	char	teamList[4096];
	char	*teamName;
	int		i, len, count;

	count = trap_FS_GetFileList( "", "team", teamList, 4096 );

	if (count) {
		teamName = teamList;
		for ( i = 0; i < count; i++ ) {
			len = strlen( teamName );
			UI_ParseTeamInfo(teamName);
			teamName += len + 1;
		}
	}

}